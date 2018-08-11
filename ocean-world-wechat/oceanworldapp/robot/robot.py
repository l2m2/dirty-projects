from werobot import WeRoBot
from werobot.config import Config

cfg = Config(
  SERVER='auto',
  HOST='0.0.0.0',
  PORT=80,
  SESSION_STORAGE=None,
  TOKEN='dirty2018',
  APP_ID='wx0328a45eebc76a6d',
  APP_SECRET='168b9d0da865f46619713dd13ed6ab28'
)

robot = WeRoBot(config=cfg)

@robot.handler
def hello(message):
    return 'Hello World!'