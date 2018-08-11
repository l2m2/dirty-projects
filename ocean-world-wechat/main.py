import werobot
import config

robot = werobot.WeRoBot(config=config.cfg)

@robot.key_click("introduction")
def introduction(message):
  return "相关内容正在更新中，敬请期待。"

@robot.key_click("animal-science")
def animal_science(message):
  return "相关内容正在更新中，敬请期待。"

robot.run()