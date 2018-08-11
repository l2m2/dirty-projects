import werobot

robot = werobot.WeRoBot(token='dirty2018')

@robot.handler
def hello(message):
  return 'Hello World!'

robot.config['HOST'] = '0.0.0.0'
robot.config['PORT'] = 80
robot.run()