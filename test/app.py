import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)



# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///project.db")



@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response



@app.route("/", methods=["GET", "POST"])
@login_required
def index():
     if (request.method == "POST"):
        itemName = request.form.get('item_name')
        description = request.form.get('description')
        category = request.form.get('category')
        price = request.form.get('price')
        stocks = request.form.get('stocks')

        try:#continuesly adds users and pass hash
            new_item = db.execute("INSERT INTO inventory (itemName, description, category, price, stocks) VALUES(?, ?, ?, ?, ?)", itemName, description, category, price, stocks)
            return redirect("/")#homepage
            #db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        except: #if user already exists
            return apology("item already exists")

    else:
        inventory_db=db.execute("SELECT * FROM inventory")
        return render_template("index.html", inventory=inventory_db)


@app.route('/add_item', methods=['POST'])
def add_item():
   if (request.method == "POST"):
        itemName = request.form.get('item_name')
        description = request.form.get('description')
        category = request.form.get('category')
        price = request.form.get('price')
        stocks = request.form.get('stocks')





@app.route("/add_cash")
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





@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
    return apology("TODO")





@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if (request.method == "POST"):
        username = request.form.get('username')
        password = request.form.get('password')
        confirmation = request.form.get('confirmation')

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

        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
            return redirect('/')
        except:
            return apology('username has already been registered')
    else:
        return render_template("register.html")





if __name__ == '__main__':
    app.run(debug=True)



