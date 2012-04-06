from django.conf.urls.defaults import patterns, include, url
from django.contrib.auth.views import login as auth_login
from django.contrib.auth.views import logout as auth_logout

# Uncomment the next two lines to enable the admin:
# from django.contrib import admin
# admin.autodiscover()

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'login.views.home', name='home'),
    # url(r'^login/', include('login.foo.urls')),

    # Uncomment the admin/doc line below to enable admin documentation:
    # url(r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
    # url(r'^admin/', include(admin.site.urls)),
    (r'^accounts/login/$', auth_login),
    (r'^accounts/logout/$', auth_logout),

)
