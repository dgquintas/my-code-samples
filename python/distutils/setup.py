from distutils.core import setup

setup(name='Hello',
    version='1.0',
    description='A simple example',
    author='Perico de los Palotes',
    scripts=['script'],
    packages=['hello_pkg'],
    data_files =[ ('/etc/foobar', ['config.cfg', ]), ] 
)

