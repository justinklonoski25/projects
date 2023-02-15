from html.parser import HTMLParser

class MyHTMLParser(HTMLParser):
    def __init__(self):
        super().__init__()
        self.paragraphs = []
        self.current_tag = None

    def handle_starttag(self, tag, attrs):
        if tag == "p":
            self.current_tag = "p"

    def handle_endtag(self, tag):
        if tag == "p":
            self.current_tag = None

    def handle_data(self, data):
        if self.current_tag == "p":
            self.paragraphs.append(data.strip())

# prompt the user to enter the filename of the HTML file
filename = input("Enter the filename of the HTML file: ")

# read in the HTML file
with open(filename) as f:
    html = f.read()

# create an instance of the HTML parser and feed it the HTML
parser = MyHTMLParser()
parser.feed(html)

# print the extracted paragraphs
for p in parser.paragraphs:
    print(p)
