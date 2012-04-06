from django.conf.urls.defaults import *
from djangoblog.blog.models import Entry
from tagging.views import tagged_object_list

info_dict = {
	'queryset': Entry.objects.filter(status=1),
	'date_field': 'pub_date',
}


urlpatterns = patterns('django.views.generic.date_based',
	(r'(?P<year>\d{4})/(?P<month>[a-z]{3})/(?P<day>\w{1,2})/(?P<slug>[-\w]+)/$', 
        'object_detail', 
        dict(info_dict, slug_field='slug',template_name='blog/detail.html')),
	(r'^(?P<year>\d{4})/(?P<month>[a-z]{3})/(?P<day>\w{1,2})/(?P<slug>[-\w]+)/$', 
        'object_detail', 
        dict(info_dict, template_name='blog/list.html')),
	(r'^(?P<year>\d{4})/(?P<month>[a-z]{3})/(?P<day>\w{1,2})/$',
        'archive_day',
        dict(info_dict,template_name='blog/list.html')),
	(r'^(?P<year>\d{4})/(?P<month>[a-z]{3})/$',
        'archive_month', 
        dict(info_dict, template_name='blog/list.html')),
	(r'^(?P<year>\d{4})/$','archive_year',
        dict(info_dict, 
            template_name='blog/list.html')))

urlpatterns += patterns('tagging.views',
    (r'^tags/(?P<tag>[a-zA-Z0-9_.-]+)/$', 
        'tagged_object_list',
        dict(queryset_or_model=Entry, template_name='tags/detail.html')))

urlpatterns += patterns('django.views.generic.date_based',
	(r'^$',
        'archive_index',
        dict(info_dict, template_name='blog/list.html')))


