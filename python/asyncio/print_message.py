import asyncio
 
@asyncio.coroutine
def just_print_messages():
    """
    This method prints a message and then sleeps for three seconds
    """
    while True:
        print('Just printing a new message every three seconds')
        yield from asyncio.sleep(3)
 
def main():
    loop = asyncio.get_event_loop()
    try:
        loop.run_until_complete(just_print_messages())
    finally:
        loop.close()
 
if __name__ == '__main__':
    main()
