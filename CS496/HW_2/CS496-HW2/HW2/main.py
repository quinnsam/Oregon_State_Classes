import webapp2

config = {'default-key':'base-data'}

app = webapp2.WSGIApplication([
    ('/view', 'view.View'),
    ('/ind', 'view.Ind'),
    ('/edit', 'handler.MainPage'),
    ('/', 'handler.MainPage'),
    ], debug=True, config=config)


