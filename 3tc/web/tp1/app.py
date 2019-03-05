from flask import Flask, render_template, request, redirect, abort, url_for
app = Flask(__name__)

@app.route('/hello.txt')
def hello():
    return redirect(url_for('static', filename='hello.txt'))

@app.route('/truth')
def truth():
    return render_template('truth.html', title='The truth', truth=42)

posts = []

@app.route('/')
@app.route('/index')
def index():
  return render_template('index.html', posts=posts)

@app.route('/post', methods=['POST'])
def post():
  posts.append(request.form['post'])
  return redirect(url_for('index'))

if __name__ == '__main__':
    app.run(debug=True)
