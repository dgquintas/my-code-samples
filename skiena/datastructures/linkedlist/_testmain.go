package main

import "linkedlist"
import "testing"
import __os__ "os"
import __regexp__ "regexp"

var tests = []testing.InternalTest{
	{"linkedlist.TestAppend", linkedlist.TestAppend},
	{"linkedlist.TestSearch", linkedlist.TestSearch},
	{"linkedlist.TestRemove", linkedlist.TestRemove},
}

var benchmarks = []testing.InternalBenchmark{	{"linkedlist.BenchmarkAppend", linkedlist.BenchmarkAppend},
	{"linkedlist.BenchmarkPrepend", linkedlist.BenchmarkPrepend},
	{"linkedlist.BenchmarkSearch", linkedlist.BenchmarkSearch},
}

var matchPat string
var matchRe *__regexp__.Regexp

func matchString(pat, str string) (result bool, err __os__.Error) {
	if matchRe == nil || matchPat != pat {
		matchPat = pat
		matchRe, err = __regexp__.Compile(matchPat)
		if err != nil {
			return
		}
	}
	return matchRe.MatchString(str), nil
}

func main() {
	testing.Main(matchString, tests, benchmarks)
}
