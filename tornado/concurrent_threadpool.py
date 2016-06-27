from concurrent.futures import ThreadPoolExecutor

import tornado.ioloop
import tornado.web
import tornado.testing


class SimpleIOLoopTests(tornado.testing.AsyncTestCase):
    @tornado.testing.gen_test
    def test_executor_future(self):
        class Executor():
            def __init__(self, io_loop=None):
                self.io_loop = io_loop or tornado.ioloop.IOLoop.instance()
                self.executor = ThreadPoolExecutor(2)

            @tornado.concurrent.run_on_executor
            def wait_and_return_a_value(self):
                return 20

            def destroy(self):
                self.executor.shutdown(1)

        @tornado.gen.coroutine
        def async_compare(callback):
            executor = Executor(self.io_loop)
            val = yield executor.wait_and_return_a_value()
            print(val)
            self.assertEqual(val, 20)

            executor.destroy()
            callback()

        async_compare(self.stop)
        self.wait()
