from flask import Flask, redirect, send_from_directory, render_template
from crontab import CronTab, time
from time import sleep
import time

app = Flask(__name__)
cron = CronTab(user='pi')


@app.route('/')
def root():
    return redirect("/home")


@app.route('/removeall')
def removeall():
    cron.remove_all()
    cron.write()
    return redirect('/')


# @app.route('/remove/<time>')
# def remove(time):
#     cron.remove(cron.find_time(time))
#     cron.write()
#     return redirect('/')


@app.route('/sveglie/<t>')
def sveglie(t):
    t = int(t)
    for i in range(3):
        job = cron.new(
            command='python /home/pi/Iot_group31/webserver/sendSignal.py')
        job.setall(time(((t - 15*i) // 60), ((t - 15*i) % 60)))

    cron.write()

    return redirect('/')


@app.route('/home')
def home():
    alarms = []
    for i, item in enumerate(cron):
        alarms.append({
            'i': i,
            'frequency': item.description(use_24hour_time_format=True),
            'time': item
        })

    page = {
        'alarms': alarms
    }
    cron.write()

    return render_template('home.html', page=page)


if __name__ == "__main__":
    app.run(host='0.0.0.0', port=80, debug=True)
