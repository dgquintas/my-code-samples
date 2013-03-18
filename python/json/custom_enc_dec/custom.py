import json
import functools

class ComplexDecoder(json.JSONDecoder):
    def __init__(self):
        json.JSONDecoder.__init__(self, object_hook=ComplexDecoder._hooks)
    @staticmethod
    def _hooks(dct):
        if '__complex__' in dct:
            complex_repr = dct['__complex__']
            return complex(*complex_repr)
        else:
            return dct

class ComplexEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, complex):
            return {'__complex__': [obj.real, obj.imag]}
        else:
            return json.JSONEncoder.default(self, obj)

dumps = functools.partial(json.dumps, cls=ComplexEncoder)
loads = functools.partial(json.loads, cls=ComplexDecoder)

in_json = dumps({'foo': 1, 'lol': 2+1j})
print(in_json)
orig = loads(in_json)
print(orig)
print(type(orig['lol']))


# another example

class _JSONDecoder(json.JSONDecoder):
    def __init__(self):
        json.JSONDecoder.__init__(self, object_hook=_JSONDecoder._hooks)
    @staticmethod
    def _hooks(dct):
        if '__array__' in dct:
            return dct['__array__']
        else:
            return dct

class _JSONEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, collections.Iterable):
            return {'__array__': list(obj)}
        else:
            return json.JSONEncoder.default(self, obj)

dumps = functools.partial(json.dumps, cls=_JSONEncoder)
loads = functools.partial(json.loads, cls=_JSONDecoder)


in_json = dumps({'foo': 1, 'lol': (1,2,3,4)})
print(in_json)
orig = loads(in_json)
print(orig)
print(type(orig['lol']))


