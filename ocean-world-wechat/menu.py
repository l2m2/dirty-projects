import werobot
import config

if __name__ == "__main__":
  robot = werobot.WeRoBot(config=config.cfg)
  client = robot.client
  client.create_menu({
      "button":[{
          "type": "click",
          "name": "测试",
          "key": "music"
      }]
  })