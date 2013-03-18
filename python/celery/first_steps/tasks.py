from celery import Celery

celery = Celery('tasks', broker='redis://localhost')

@celery.task
def add(x, y):
    return x + y
