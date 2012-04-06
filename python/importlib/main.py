import importlib
import sys

if __name__ == "__main__":
    cfg = importlib.import_module(sys.argv[1][:-3])
    print cfg.setting2
