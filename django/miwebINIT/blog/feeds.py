from miweb.blog.models import Entry
from django.contrib.syndication.feeds import Feed
from django.utils.feedgenerator import Atom1Feed
from django.conf import settings

class RssSiteNewsFeed(Feed):
  title = "ptrtovoid.net blog"
  title_template = "feeds/rss_title.html"
  link = "/blog/"
  description = "New stuff being posted to ptrtovoid.net/blog"
  description_template = "feeds/rss_description.html"


  def items(self):
    num_posts = settings.BLOG_FEED_POSTS
    return Entry.objects.filter(published=True).order_by('-pub_date')[:num_posts]

class AtomSiteNewsFeed(RssSiteNewsFeed):
  feed_type = Atom1Feed
  subtitle = RssSiteNewsFeed.description


