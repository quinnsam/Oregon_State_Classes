import webapp2
import time

class MainPage(webapp2.RequestHandler):
    def get(self):
        #self.response.headers['Content-Type'] = 'text/plain'
        self.response.write('Hello, World!')

class TimePage(webapp2.RequestHandler):
    def get(self):
        self.response.write(time.asctime(time.localtime()))

class CatchAllHandler(webapp2.RequestHandler):
    def get(self):
        self.response.write('..And, where do you think you are going?<br><img src="/img/404.jpg">')

app = webapp2.WSGIApplication([
    ('/', MainPage),
    ('/time/?', TimePage),
    ('/time/.*', CatchAllHandler)
], debug=True)
