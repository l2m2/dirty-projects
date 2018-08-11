import werobot
from werobot.config import Config

if __name__ == "__main__":
  config = Config(
    SERVER='auto',
    HOST='0.0.0.0',
    PORT=80,
    SESSION_STORAGE=None,
    TOKEN='dirty2018',
    APP_ID='wx0328a45eebc76a6d',
    APP_SECRET='168b9d0da865f46619713dd13ed6ab28'
  )

  robot = werobot.WeRoBot(config=config)
  client = robot.client
  client.create_menu({
      "button":[{
          "type": "click",
          "name": "今日歌曲",
          "key": "music"
      }]
  })