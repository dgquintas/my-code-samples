class C(object):
  results = []

  def appendResult(cls, result):
    cls.results.append(result)
  appendResult = classmethod(appendResult)

  def getResults(cls):
    return cls.results
  getResults = classmethod(getResults)



def main():
  c = C()

  C.appendResult(2)
  c.appendResult(3)

  print c.getResults()
  print C.getResults()


if __name__ == "__main__":
  main()

