import web, model, os

### Url mappings
urls = (
    '/', 'Index',
    '/login', 'Login',
    '/user', 'User',
    '/upload', 'Upload',
    '/logout', 'Logout',
    '/error_page', 'ErrorPage',
    '/download', 'Download'
)


### Templates
t_globals = {
    'datestr': web.datestr
}

render = web.template.render('templates', globals = t_globals)
web.config.debug = False
app = web.application(urls, globals())
session = web.session.Session(app, web.session.DiskStore('sessions'), initializer={'user_id':''})

class Index:
    def GET(self):
        return render.index()

class Login:
    def GET(self):
        return render.login()

    def POST(self):
        user_id =  web.input().user_id
        pwd = web.input().pwd
        ident = model.get_user(user_id)
        '''
        try:
            if hashlib.sha1("sAlT754-"+passwd).hexdigest() == ident['pass']:
                session.login = 1
                session.privilege = ident['privilege']
                render = create_render(session.privilege)
                return render.login_ok()
            else:
                session.login = 0
                session.privilege = 0
                render = create_render(session.privilege)
                return render.login_error()
        except:
            session.login = 0
            session.privilege = 0
            render = create_render(session.privilege)
            return render.login_error()
            '''
        try:
            if pwd == ident['pwd']:
                session.user_id = user_id
                raise web.seeother('/user')
            else:
                return render.error_page('Wrong password!')
        except:
            return render.error_page("User not found!")

class User:
    def GET(self):
        #print session.user_id
        user = model.get_user(session.user_id)
        return render.user(user)

class Upload:

    def GET(self):
        return render.upload()

    def POST(self):
        x = web.input(myfile = {})
        filedir = 'uploaded_files' # change this to the directory you want to store the file in.
        if 'myfile' in x: # to check if the file-object is created
            filepath = x.myfile.filename.replace('\\','/') # replaces the windows-style slashes with linux ones.
            filename = filepath.split('/')[-1] # splits the and chooses the last part (the filename with extension)
            fout = open(filedir +'/'+ filename,'wb') # creates the file where the uploaded file should be stored
            fout.write(x.myfile.file.read()) # writes the uploaded file to the newly created file.
#            fout.write(x.myfile.value) # writes the uploaded file to the newly created file.
            fout.close() # closes the file, upload complete.
        
        rootdir = './history_versions'                                 
        result_f = 0.0
        for parent, dirnames, filenames in os.walk(rootdir):
            for file_ in filenames:
                result = os.popen('./tools/detector ./' + filedir +'/'+ filename + ' ' + os.path.join(parent,file_)).read()
                result_f = max(result_f, float(result))
        #only show last result
        model.update_results(user_id = session.user_id, result_history = result_f, result_uploaded = 0)
        raise web.seeother('/user')

#BUF_SIZE = 262144
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
                #c = f.read(BUF_SIZE)
                c = f.read(262144)
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

class Logout:
    def GET(self):
        session.kill()
        return render.logout()

class ErrorPage:
    def GET(self):
        return render.error_page()
    #def POST(self):



if __name__ == '__main__':
    app.run()
