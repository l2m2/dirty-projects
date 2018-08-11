import config
from werobot import WeRoBot

robot = WeRoBot(config=config.cfg)

@robot.handler
def hello(message):
    return 'Hello World!'