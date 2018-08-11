import werobot
from werobot.config import Config

config = Config(
  SERVER='auto',
  HOST='0.0.0.0',
  PORT=80,
  TOKEN='dirty2018',
  APP_ID='wx0328a45eebc76a6d',
  APP_SECRET='168b9d0da865f46619713dd13ed6ab28'
)

robot = werobot.WeRoBot(config=config)

@robot.handler
def hello(message):
  return 'Hello World!'

robot.run()