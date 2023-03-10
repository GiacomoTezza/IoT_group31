from flask import Flask, redirect, send_from_directory, render_template
from crontab import CronTab, time
from time import sleep
from time import time as unixtime
from os import system, getlogin, getcwd


app = Flask(__name__)
cron = CronTab(user=getlogin())



@app.route('/')
def root():
    return redirect("/home")

# Removes all cron entries
@app.route('/removeall')
def removeall():
    cron.remove_all()
    cron.write()
    return redirect('/')


# Removes a specific cron entry specified by the id value
@app.route('/remove_snack/<id>')
def remove_snack(id):
    cron.remove_all(comment=id)
    cron.write()
    return redirect('/')

# Dispenses a snack
@app.route('/dispense_now/')
def dispense_now():
    print(getcwd())
    system(f'python {getcwd()}/sendSignal.py')
    return redirect('/')

# Creates a cron job for dispensing the snack
@app.route('/set_snack/<t>')
def set_snack(t):
    t = int(t)

    job = cron.new(command=f'python {getcwd()}/sendSignal.py', comment=str(unixtime()))
    job.setall(time((t// 60), (t % 60)))

    cron.write()

    return redirect('/')


@app.route('/home')
def home():
    alarms = []
    for i, item in enumerate(cron):
        alarms.append({
            'frequency': item.description(use_24hour_time_format=True)[3:],
            'id': item.comment
        })

    alarms.sort(key=lambda x: x['frequency'].split(":")[0] * 60 + x['frequency'].split(":")[1])
    page = {
        'alarms': alarms
    }

    cron.write()

    return render_template('home.html', page=page)


if __name__ == "__main__":
    app.run(host='0.0.0.0', port=8080, debug=True)
