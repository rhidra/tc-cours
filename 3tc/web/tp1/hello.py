from flask import Flask, request, url_for, redirect, abort
app = Flask(__name__)

@app.route('/name/<user>')
def hey(name):
    app.logger.warning("Routage vers /")
    return 'Coucou %s !'

@app.route('/excellence')
def excellence():
    app.logger.info("Debut")
    app.logger.error("Erreur !!!")
    return "Stanford"

@app.route('/plop/')
def plop():
    return 'Plop !'

@app.route('/show-routes')
def show_routes():
    routes = ''
    with app.test_request_context():
        routes = routes + url_for('excellence') + '\n'
        routes = routes + url_for('plop') + '\n'
        routes = routes + url_for('excellence', aeres=True) + '\n'
    return routes

@app.route('/vortex')
def vortex():
    return redirect(url_for('excellence', vortex=1))

@app.route('/fail')
def fail():
    abort(500)

@app.errorhandler(500)
def internal_error(error):
    return "Whoops !"

@app.errorhandler(404)
def not_found(error):
    return "Page not found !!!"

if __name__ == '__main__':
    app.logger.info("Lancement de l'application !")
    app.run(debug=True)
