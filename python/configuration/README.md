# Tiny conf

A simple configuration holder inspired and largely based on  Django's `.conf`. 

# Installation 
Simply place the `conf` folder on your Python path or wherever you want as long
as you are able to import it.

**Important**: modify the value of `ENVIRONMENT_VARIABLE` to something specific
to your project.

# Usage

Configuration is given in Python modules. Anything goes. The module will be
imported and as usual the top-level symbols will be available. 

## Example

```
# settings.conf.py
...
CONTROLLER = {'num_workers':   8,
              'num_timers':    4}
...
```

```
# main.py
from conf import settings
...
workers = WorkersPool(settings.CONTROLLER['num_workers'])
...
```

Any module importing `conf` will have access to the same config, by virtue
of the Python's "module-singleton" nature.

The settings file to be used is defined by the value of an environment variable
with the same name as the value given to `ENVIRONMENT_VARIABLE`. For example,
if `ENVIRONMENT_VARIABLE = 'FOO'` in `conf/__init__.py`, the environment
variable `FOO` must exist and point to the Python file holding the
configuration directives prior to starting the application using `conf`. 
For example, `$ FOO='../foobar.conf.py' python main.py`
