from django.conf.urls.defaults import *
from tagging.models import Tag
from miweb.blog.models import Entry
from miweb.blog.feeds import RssSiteNewsFeed, AtomSiteNewsFeed
from django.conf import settings 

entries_per_page = settings.BLOG_ENTRIES_PER_PAGE 

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
     dict(queryset_or_model=Entry, paginate_by=entries_per_page, allow_empty=True, template_object_name='entries', template_name='blog/entry_list.html'),
     name='blog-list-tag'),
)

urlpatterns += patterns('miweb.blog.views',
   url(r'^comment/$',    'comment',  name='blog-post-comment'),
   )

info_dict = {
    'queryset': Entry.objects.filter(published=True),
    'date_field': 'pub_date',
}


urlpatterns += patterns('django.views.generic.date_based',
   url(r'^(?P<year>\d{4})/(?P<month>\d{2})/(?P<day>\d{2})/(?P<slug>[-\w]+)/$', 
     'object_detail', 
     dict(info_dict, template_object_name='entry', template_name='blog/entry_detail.html', month_format='%m'),
     name='blog-entry'),
   url(r'^(?P<year>\d{4})/(?P<month>\d{2})/(?P<day>\w{1,2})/$',               'archive_day',   info_dict),
   url(r'^(?P<year>\d{4})/(?P<month>\d{2})/$',                                
     'archive_month', 
     dict(info_dict, template_object_name='entries', month_format='%m', template_name='blog/entry_list.html'),
     name='blog-list-month'),
   url(r'^(?P<year>\d{4})/$',
     'archive_year',  
     dict(info_dict, make_object_list='True', template_object_name='entries', template_name='blog/entry_list.html'),
     name='blog-list-year'),
)


feeds = {
    'rss': RssSiteNewsFeed,
    'atom': AtomSiteNewsFeed,
}


urlpatterns += patterns('',
    url(r'^feeds/(?P<url>.*)/$', 'django.contrib.syndication.views.feed', {'feed_dict': feeds}, name="feeds"),
)



