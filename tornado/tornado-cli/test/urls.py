from handlers.welcome import WelcomeHandler

url_patterns = [
    (r"/", WelcomeHandler),
]
