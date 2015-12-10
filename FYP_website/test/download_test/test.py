import web,os

urls = (
    '/', 'Index',
    '/download', 'Download',
)

### Templates
t_globals = {
    'datestr': web.datestr
}

render = web.template.render('templates', globals = t_globals)
app = web.application(urls, globals())

class Index:
    def GET(self):
        return render.index()


BUF_SIZE = 262144
class Download:
    def GET(self):
        file_name = 'Lab.zip'
        #file_path = os.path.join('file_path', file_name)
        file_path  = os.path.join('', file_name)
        f = None
        try:
            f = open(file_path, "rb")
            web.header('Content-Type','application/octet-stream')
            web.header('Content-disposition', 'attachment; filename=%s' % file_name)
            while True:
                c = f.read(BUF_SIZE)
                if c:
                    yield c
                else:
                    break
        except Exception, e:
            print e
            yield 'Error'
        finally:
            if f:
                f.close()

if __name__ == '__main__':
    app.run()
