import webapp2
from google.appengine.api import oauth

config = {'default-key':'base-data'}

app = webapp2.WSGIApplication([
    ('/api', 'api.API'),
    ], debug=True)

# APP router stuff
app.router.add(webapp2.Route(r'/api/<id:[0-9]+><:/?>', 'api.API'))
