from django.conf.urls.defaults import *
from tagging.models import Tag
from blog.models import Entry
from blog.feeds import RssSiteNewsFeed, AtomSiteNewsFeed
from django.conf import settings 

entries_per_page = settings.BLOG_ENTRIES_PER_PAGE 

info_dict = {
    'queryset': Entry.objects.all(),
    'date_field': 'pub_date',
}
feeds = {
    'rss': RssSiteNewsFeed,
    'atom': AtomSiteNewsFeed,
}

urlpatterns = patterns('django.views.generic.list_detail',
   url(r'^$',                                                                    
     'object_list', 
     dict(queryset=Entry.objects.filter(published=True), template_object_name='entries', paginate_by=entries_per_page, template_name='blog/entry_archive.html'),
     name='blog-list-newest'), 
   url(r'^page/(?P<page>\d+)/$',                                                                    
     'object_list', 
     dict(queryset=Entry.objects.filter(published=True), template_object_name='entries', paginate_by=entries_per_page, template_name='blog/entry_archive.html'),
     name='blog-list-newest-page'),
)

urlpatterns += patterns('',
   url(r'^tag/(?P<tag>[^/]+)/$',                                                                    
     'tagging.views.tagged_object_list', 
     dict(queryset_or_model=Entry, allow_empty=True, template_object_name='entries', template_name='blog/entry_list.html'),
     name='blog-list-tag'),
)

urlpatterns += patterns('blog.views',
   url(r'^comment/$',    'comment',  name='blog-post-comment'),
   )



urlpatterns += patterns('django.views.generic.date_based',
   url(r'^(?P<year>\d{4})/(?P<month>\d{2})/(?P<day>\d{2})/(?P<slug>[-\w]+)/$', 
     'object_detail', 
     dict(info_dict, template_object_name='entry', template_name='blog/entry_detail.html', month_format='%m'),
     name='blog-entry'),
   
   url(r'^(?P<year>\d{4})/(?P<month>\d{2})/(?P<day>\d{2})/$',               
     'archive_day',   
     dict(info_dict, template_object_name='entries', allow_empty=True, month_format='%m', template_name='blog/entry_list.html'),
     name='blog-list-day'),

   url(r'^(?P<year>\d{4})/(?P<month>\d{2})/$',                                
     'archive_month', 
     dict(info_dict, template_object_name='entries', allow_empty=True,month_format='%m', template_name='blog/entry_list.html'),
     name='blog-list-month'),

   url(r'^(?P<year>\d{4})/$',
     'archive_year',  
     dict(info_dict, make_object_list='True', template_object_name='entries', allow_empty=True,template_name='blog/entry_list.html'),
     name='blog-list-year'),
)




urlpatterns += patterns('',
    url(r'^feeds/(?P<url>.*)/$', 'django.contrib.syndication.views.feed', {'feed_dict': feeds}, name="feeds"),
)



