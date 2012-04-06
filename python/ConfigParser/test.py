from ConfigParser import SafeConfigParser, NoOptionError


config = SafeConfigParser()
config.read('config')

print config.get('My section','foodir')
print config.get('My section','default_dep')
print repr(config.get('My section','empty'))
print config.options('My section')
print config.items('My section')
try:
    print config.get('My section','idontexist')
except NoOptionError:
    pass

print "Reading another config file..."
config.read('config2')
print "It gets appendend: ", config.sections()

