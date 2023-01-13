from flask import Flask, redirect, send_from_directory, render_template
from crontab import CronTab, time
from time import sleep
from time import time as unixtime
from os import system

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


@app.route('/remove_snack/<id>')
def remove_snack(id):
    cron.remove_all(comment=id)
    cron.write()
    return redirect('/')

@app.route('/dispense_now/')
def dispense_now(id):
    system('python /home/pi/Iot_group31/webserver/sendSignal.py')
    return redirect('/')


@app.route('/set_snack/<t>')
def set_snack(t):
    t = int(t)

    job = cron.new(command='python /home/pi/Iot_group31/webserver/sendSignal.py', comment=str(unixtime()))
    job.setall(time((t// 60), (t % 60)))

    cron.write()

    return redirect('/')


@app.route('/home')
def home():
    alarms = []
    for i, item in enumerate(cron):
        alarms.append({
            'i': i,
            'frequency': item.description(use_24hour_time_format=True)[3:],
            'time': item,
            'id': item.comment
        })

    page = {
        'alarms': alarms
    }

    cron.write()

    return render_template('home.html', page=page)


if __name__ == "__main__":
    app.run(host='0.0.0.0', port=8080, debug=True)
