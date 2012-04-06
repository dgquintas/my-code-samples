import logging

# set up logging to file
#logging.basicConfig([**kwargs])
#
#    Does basic configuration for the logging system by creating a StreamHandler
#    with a default Formatter and adding it to the root logger. The functions
#    debug(), info(), warning(), error() and critical() will call basicConfig()
#    automatically if no handlers are defined for the root logger.
#
#    This function does nothing if the root logger already has handlers
#    configured for it.
#

#in this case, it'd create a FileHandler, because we specify the "filename" kwarg
logging.basicConfig(level=logging.DEBUG,
                    format='%(asctime)s %(name)-12s %(levelname)-8s %(message)s',
                    #datefmt='%m-%d %H:%M',
                    filename='test.log',
                    filemode='w')
# define a Handler which writes INFO messages or higher to the sys.stderr
console = logging.StreamHandler()
console.setLevel(logging.INFO)
# set a format which is simpler for console use
formatter = logging.Formatter('%(name)-12s: %(levelname)-8s %(message)s')
# tell the handler to use this format
console.setFormatter(formatter)
# add the handler to the root logger
logging.getLogger('').addHandler(console)

# Now, we can log to the root logger, or any other logger. First the root...
logging.info('Jackdaws love my big sphinx of quartz.')

# Now, define a couple of other loggers which might represent areas in your
# application:

logger1 = logging.getLogger('myapp.area1')
logger2 = logging.getLogger('myapp.area2')

logger1.debug('Quick zephyrs blow, vexing daft Jim.')
logger1.info('How quickly daft jumping zebras vex.')
logger2.warning('Jail zesty vixen who grabbed pay from quack.')
logger2.error('The five boxing wizards jump quickly.')
