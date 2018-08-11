import werobot
from werobot.config import Config

config = Config(
  HOST='0.0.0.0',
  PORT=80,
  TOKEN='dirty2018',
  APP_ID='wx6aff19a293e7b2b0',
  APP_SECRET='ccdb695e5539091c05690da508bf584e'
)

robot = werobot.WeRoBot(config=config)

@robot.handler
def hello(message):
  return 'Hello World!'

robot.run()