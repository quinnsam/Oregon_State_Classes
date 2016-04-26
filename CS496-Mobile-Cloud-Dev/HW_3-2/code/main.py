import webapp2
from google.appengine.api import oauth

config = {'default-key':'base-data'}

app = webapp2.WSGIApplication([
    ('/pubkey', 'api.PubKey'),
    ('/people', 'api.People'),
    ('/*', 'api.API'),
    ], debug=True)

# APP router stuff
app.router.add(webapp2.Route(r'/pubkey/<id:[0-9]+><:/?>', 'api.PubKey'))
app.router.add(webapp2.Route(r'/pubkey/<id:[A-z\s]+><:/?>', 'api.PubKeySearch'))
app.router.add(webapp2.Route(r'/pubkey/del/<id:[0-9]+><:/?>', 'api.DelPubKey'))
app.router.add(webapp2.Route(r'/people/<id:[0-9]+><:/?>', 'api.People'))
app.router.add(webapp2.Route(r'/people/<id:[A-z\s]+><:/?>', 'api.PeopleSearch'))
app.router.add(webapp2.Route(r'/people/del/<id:[0-9]+><:/?>', 'api.DelPeople'))
