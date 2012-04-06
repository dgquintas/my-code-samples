import bs4
import sys
import re
from urllib.request import urlopen

# get a list of links matching a given pattern
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("%s <url> <pattern>")
        sys.exit(1)
    url, pattern = sys.argv[1:3]

    data = urlopen(url).read()
    
    soup = bs4.BeautifulSoup(data)

    links = soup(name='a', href=re.compile(pattern))
    files = [ link['href'] for link in links ]

    print('\n'.join(files))

    
