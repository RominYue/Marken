import codecs
from pyquery import PyQuery
import HTMLParser  

def translate(s):
    return HTMLParser.HTMLParser().unescape(s.replace('&#8594;', '\t'))

spec = open('spec.html', 'r').read()
d = PyQuery(spec)
for i in range(0, 443):
    num = str(i + 1)
    divName = 'example-' + num
    exampleDiv = d('#' + divName)
    dd = PyQuery(exampleDiv)
    markdown = str(PyQuery(dd('.markdown'))('code'))[6:-7]
    html = str(PyQuery(dd('.html'))('code'))[6:-7]
    codecs.open(num + '.in', 'w', 'utf-8').write(translate(markdown))
    codecs.open(num + '.out', 'w', 'utf-8').write(translate(html))
open('case_common', 'w').write('\n'.join(['common/' + str(i + 1) for i in range(0, 443)]))