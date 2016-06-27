import unittest

from hello import Factorial


class FactorialTestCase(unittest.TestCase):
    def test_negative_factorial(self):
        self.assertRaises(ValueError, Factorial, -1)

    def test_factorial(self):
        self.assertEqual(120, Factorial(5))


if __name__ == '__main__':
    unittest.main()
