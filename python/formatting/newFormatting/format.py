# see http://docs.python.org/library/string.html#format-examples

'{0}, {1}, {2}'.format('a', 'b', 'c')
'{}, {}, {}'.format('a', 'b', 'c')  # 2.7+ only
'{2}, {1}, {0}'.format('a', 'b', 'c')
'{2}, {1}, {0}'.format(*'abc')      # unpacking argument sequence
'{0}{1}{0}'.format('abra', 'cad')   # arguments' indices can be repeated

'Coordinates: {latitude}, {longitude}'.format(latitude='37.24N', longitude='-115.81W')
coord = {'latitude': '37.24N', 'longitude': '-115.81W'}
'Coordinates: {latitude}, {longitude}'.format(**coord)

coord = (3, 5)
'X: {0[0]};  Y: {0[1]}'.format(coord)

"repr() shows quotes: {!r}; str() doesn't: {!s}".format('test1', 'test2')

'{:<30}'.format('left aligned')
'{:>30}'.format('right aligned')
'{:^30}'.format('centered')
'{:*^30}'.format('centered')  # use '*' as a fill char


'{:+f}; {:+f}'.format(3.14, -3.14)  # show it always
'{: f}; {: f}'.format(3.14, -3.14)  # show a space for positive numbers
'{:-f}; {:-f}'.format(3.14, -3.14)  # show only the minus -- same as '{:f}; {:f}'

# format also supports binary numbers
"int: {0:d};  hex: {0:x};  oct: {0:o};  bin: {0:b}".format(42)
# with 0x, 0o, or 0b as prefix:
"int: {0:d};  hex: {0:#x};  oct: {0:#o};  bin: {0:#b}".format(42)

'{:,}'.format(1234567890)

points = 19.5
total = 22
'Correct answers: {:.2%}.'.format(points/total)


import datetime
d = datetime.datetime(2010, 7, 4, 12, 15, 58)
'{:%Y-%m-%d %H:%M:%S}'.format(d)

for align, text in zip('<^>', ['left', 'center', 'right']):
    '{0:{fill}{align}16}'.format(text, fill=align, align=align)


octets = [192, 168, 0, 1]
'{:02X}{:02X}{:02X}{:02X}'.format(*octets)
int(_, 16)

width = 5
for num in range(5,12):
    for base in 'dXob':
        print '{0:{width}{base}}'.format(num, base=base, width=width),
    print

