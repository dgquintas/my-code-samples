from django.conf.urls.defaults import *
from mysite.views import hello, current_datetime, hours_ahead, display_meta
from mysite.books import views as viewsBooks
from mysite.contact import views as viewsContacts

# Uncomment the next two lines to enable the admin:
from django.contrib import admin
admin.autodiscover()

urlpatterns = patterns('',
    # Example:
    # (r'^mysite/', include('mysite.foo.urls')),

    # Uncomment the admin/doc line below and add 'django.contrib.admindocs' 
    # to INSTALLED_APPS to enable admin documentation:
    # (r'^admin/doc/', include('django.contrib.admindocs.urls')),

    # Uncomment the next line to enable the admin:
    # (r'^admin/', include(admin.site.urls)),
    (r'^hello/$', hello),
    (r'^meta/$', display_meta),
    (r'^time/$', current_datetime),
    (r'^time/plus/(\d{1,2})/$', hours_ahead),
    (r'^admin/', include(admin.site.urls)),

    (r'^search/$', viewsBooks.search),

    (r'^contact/$', viewsContacts.contact),
    (r'^contact/thanks/$', viewsContacts.thanks),
    


)

