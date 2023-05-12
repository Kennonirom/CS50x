from pyfiglet import Figlet
import sys
import random



fontIsRandom = False

if (len(sys.argv) == 1):
    FontIsRandom = True
elif (len(sys.argv) == 3):
    FontIsRandom = False
else:
    sys.exit("Command line argument not expected")

figlet = Figlet()

availableFonts = figlet.getFonts()

if fontIsRandom == False:
    if (sys.argv[1] not in ["-f", "--font"]):
            sys.exit("Second command-line argumnet incorrect")
    try:
         font = figlet.setFont(font=sys.argv[2])
    except:
         sys.exit("Font Doesn't Exist")
else:
     font = random.choice(availableFonts)

txt = input("input: ")

print(figlet.renderText(txt))










# def mycode():
#     if (sys.argv[1] != "-f" or sys.argv[1] != "--font"):
#         print('Invalid usage')
#         sys.exit(1)

#     user_input = input("Input: ")
#     print("Output: ")

#     figlet = Figlet()

#     random_fonts = figlet.getFonts()


#     try:
#         if len(sys.argv) == 1:
#             s = random.choice(random_fonts)
#             figlet.setFont(font= s)
#             print(figlet.renderText(user_input))

#         else:
#             figlet.setFont(font= sys.argv[2])
#             print(figlet.renderText(user_input))

#     except IndexError:
#         print('Invalid Usage')


#     sys.exit(0)



