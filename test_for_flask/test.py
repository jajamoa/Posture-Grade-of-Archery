from flask import Flask, render_template, jsonify, request

from flask_cors import CORS

app = Flask(__name__)
CORS(app, supports_credentials=True)




@app.route('/page-1')
def page1():
    return app.send_static_file('page-1.html')


@app.route('/get_param')
def param():
    msg = '60'
    file = open("C://Users//jsjtx//Desktop//bowbow//Message//2.txt", "r")
    score = file.read()
    file.close()
    print('score is ', score)
    fuck = request.args['id']
    #print('fuck is ', fuck)
    if fuck == '1':
        msg = '61'
        object = open("C://Users//jsjtx//Desktop//bowbow//Message//1.txt", "w")
        object.write("1")
        object.close()
    elif fuck == '2':
        msg = '62'
        object = open("C://Users//jsjtx//Desktop//bowbow//Message//1.txt", "w")
        object.write("2")
        object.close()
    elif fuck == '3':
        msg = '63'
        object = open("C://Users//jsjtx//Desktop//bowbow//Message//1.txt", "w")
        object.write("3")
        object.close()
    elif fuck == '4':
        msg = '64'
        object = open("C://Users//jsjtx//Desktop//bowbow//Message//1.txt", "w")
        object.write("4")
        object.close()
    elif fuck == '0':
        object = open("C://Users//jsjtx//Desktop//bowbow//Message//1.txt", "w")
        object.write("0")
        object.close()
    elif fuck == '5':
        object = open("C://Users//jsjtx//Desktop//bowbow//Message//1.txt", "w")
        object.write("5")
        object.close()
    elif fuck == '6':
        object = open("C://Users//jsjtx//Desktop//bowbow//Message//1.txt", "w")
        object.write("6")
        object.close()

    print('hello '+msg)
    return jsonify({
        'msg': score
    })


def start():
    pass


def select_mode(number):
    pass


def get_score():
    pass


if __name__ == '__main__':
    app.run(host='0.0.0.0')


