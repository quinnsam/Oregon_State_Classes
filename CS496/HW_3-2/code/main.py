import webapp2
from google.appengine.api import oauth

config = {'default-key':'base-data'}

app = webapp2.WSGIApplication([
    ('/pubkey', 'api.PubKey'),
    ('/people', 'api.People'),
    ], debug=True)

# APP router stuff
app.router.add(webapp2.Route(r'/pubkey/<id:[0-9]+><:/?>', 'api.PubKey'))
app.router.add(webapp2.Route(r'/people/<id:[0-9]+><:/?>', 'api.PubKey'))
