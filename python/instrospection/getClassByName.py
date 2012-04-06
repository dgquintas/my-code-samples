#from http://stackoverflow.com/questions/452969/does-python-have-an-equivalent-to-java-class-forname/452981

def get_class( clazz ):
    parts = clazz.split('.')
    module = ".".join(parts[:-1])
    m = __import__( module )
    for comp in parts[1:]:
        m = getattr(m, comp)            
    return m

D = get_class("datetime.datetime")
print D
print D.now()

