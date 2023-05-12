import os
import datetime

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"] #identifies who is loged-in in the data base
    #selects the symbol , sum of shares as shares and price from tractions where in teh user id
    transactions_db = db.execute("SELECT symbol, SUM(shares) AS shares, price FROM transactions WHERE user_id=?", user_id)
    #outputs the cash , and user table row
    cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = cash_db[0]["cash"] #selects the data in the cash row
    #returns the needed values as objects to used in the index html
    return render_template("index.html", database = transactions_db, cash=cash)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    #displays the buy html
    if request.method == "GET":
        return render_template("buy.html")

    else:
    #objectify the form(input box) in the html file
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        #if symbol and shares is empty print apolody
        if not symbol:
            return apology("Must give Symbol")
        if not shares:
            return apology("Must give shares")
        #gets the equivalent symbol in the API
        stock = lookup(symbol.upper()) #makes sure that the symbol is in all upper case

        if stock == None: #if the symbol is not in tHE API
            return apology("Symbol does not exist")

        if shares < 0: #makes sure that inputed share is positive int
            return apology("Share not allowed")
        #multiplies the num of shares to the stock price
        transaction_value = shares * stock["price"]
        #identifies who is logged in
        user_id = session["user_id"]
        #outputs the cash , and user table row
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"] #selects the speficific data in cash row
        #makes sure taht you have enough cash to buy the share
        if user_cash < transaction_value:
            return apology("not enough money")
        #subtracts the transaction cash with our cash
        update_cash = user_cash - transaction_value
        #updates the cash row in users table
        db.execute("UPDATE users SET cash= ? WHERE id= ?",update_cash, user_id)

        date = datetime.datetime.now() #sets the time for (now) for the transaction
        #inserts the needed information into the new transactions table
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES(?, ?, ?, ?, ?)", user_id, stock["symbol"], shares, stock["price"], date)

        flash("Bought!")#modal or a drop down

        return redirect("/") #returns user to main page




@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"] #identifies who is logged in
    #selects all rows in transactions table
    transactions_db = db.execute("SELECT * FROM transactions WHERE user_id = ?",user_id)
    #renders history html and objectified all the data from teh transactions db
    return render_template("history.html", transactions = transactions_db)




@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """adds cash the account"""
    user_id = session["user_id"] #identifies the user

    if request.method == "GET": #renders the add html
        return render_template("add.html")
    else:
        new_cash = int(request.form.get("new_cash")) #objectified teh form(input box)

        if not new_cash: #if input box empty
            return apology("You must input amount")

        user_id = session["user_id"]#identifies the user
        #outputs the cash , and user table row
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"]#selects the specific data in cash row
        #adds the inputted value into the user cash
        update_cash = user_cash + new_cash
        #updates the cash in the data sbe
        db.execute("UPDATE users SET cash= ? WHERE id= ?",update_cash, user_id)

        return redirect("/")#to homepage






@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET": #renders quote html
        return render_template("quote.html")

    else: #objectify the inputbox named symbol
        symbol = request.form.get("symbol")

        if not symbol: #if input box is empty
            return apology("Must give Symbol")
        #looks for the symbol in the API
        stock = lookup(symbol.upper())#makes it all caps

        if stock == None: #if symbol does not exist in the stock API
            return apology("Symbol does not exist")
        #retusn the name, price and symbol of the stock that is called in teh stokc API
        return render_template("quoted.html", name=stock["name"], price= stock["price"], symbol= stock["symbol"])



@app.route("/register", methods=["GET", "POST"])
def register():

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "GET":
        return render_template("register.html")

    else: #objectifies all teh name in the html
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        #chekcs if empty
        if not username:
            return apology("Must Give Username")

        if not password:
            return apology("Must Give password")

        if not confirmation:
            return apology("Must give Pass Confirmaiton")
        #pass must ==  to confirmation
        if password != confirmation:
            return apology("Password Do Not Match ")
        #turns pass into encrypted int
        hash = generate_password_hash(password)

        try:#continuesly adds users and pass hash
            new_user = db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, hash)
        except: #if user already exists
            return apology("username already exists")
        #logs in the new registered user
        session["user_id"] = new_user

        



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":
        user_id = session["user_id"]#identifies teh user
        #selects the specific stock in the transactions db, group by symbol (combines similar symbols) as wells as the sum fo shares
        #thats is not negative
        symbols_user = db.execute("SELECT symbol FROM transactions WHERE user_id= ? GROUP BY symbol HAVING SUM(shares) > 0",user_id)
        #redners sell html, as well as all the available stocks taht can be sold
        return render_template("sell.html", symbols = [row["symbol"] for row in symbols_user])

    else: #objectifies the symbol and shares
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        #input box mus not be empty
        if not symbol:
            return apology("Must give Symbol")
        if not shares:
            return apology("Must give shares")
        #looks for the symbol in the stock API
        stock = lookup(symbol.upper())

        if stock == None: #if symbol does not exist teh API
            return apology("Symbol does not exist")

        if shares < 0: #makes sure that the num of share is positive num
            return apology("Share not allowed")
        #multiplies the shares and thr price of the said stock
        transaction_value = shares * stock["price"]

        user_id = session["user_id"] #identifies the user
         #outputs the cash , and user table row
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        user_cash = user_cash_db[0]["cash"] #selects specfific data in cash row
        #selects your current shares , user , id and symbol
        user_shares = db.execute("SELECT shares FROM transactions WHERE user_id= ? AND symbol = ? GROUP BY symbol", user_id, symbol)
        user_shares_real = user_shares[0]["shares"]#slects shares spefically

        if shares > user_shares_real: #checks if shares you inputted is less tahn teh shares you currently have
            return apology("YOu do not have these amount of shares")
        #adds users current cash and the value of the shares sold
        update_cash = user_cash + transaction_value
        #updates the users cash
        db.execute("UPDATE users SET cash= ? WHERE id= ?",update_cash, user_id)

        date = datetime.datetime.now()#checks teh time now

        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES(?, ?, ?, ?, ?)", user_id, stock["symbol"], (-1)*shares, stock["price"], date)

        flash("Sold!")#modal / dropdown

        return redirect("/")# to homepage