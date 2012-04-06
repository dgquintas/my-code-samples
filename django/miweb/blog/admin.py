from blog.models import Entry, Comment, Image, BodyCache, Link
from django.contrib import admin

class CommentAdmin(admin.ModelAdmin):
  pass

class LinkAdmin(admin.ModelAdmin):
  pass

class BodyCacheAdmin(admin.ModelAdmin):
  pass

class CommentInline(admin.TabularInline):
  model = Comment
  extra = 1

class ImageAdmin(admin.ModelAdmin):
  pass

class EntryAdmin(admin.ModelAdmin):
  prepopulated_fields = {"slug": ("title",) }
  fieldsets = (
      (None,        {'fields': ['title', 'snip', 'slug', 'tags']}),
      ('Content', {'fields': ['body', 'published', ], }),
      ('Images', {'fields': ['images', ], }),
      ('Links', {'fields': ['links', ], }),
      ('Date info', {'fields': ['pub_date'], 'classes': ['collapse']}),
      ('Cached Data', {'fields': ['cached_body'], 'classes': ['collapse']}),
      )
  list_display = ('title', 'pub_date', 'published')
  list_filter = ('pub_date', 'published')
  date_hierarchy = 'pub_date'

  inlines = (
      CommentInline,
      )



admin.site.register(Entry, EntryAdmin)
admin.site.register(Comment, CommentAdmin)
admin.site.register(Image, ImageAdmin)
admin.site.register(Link, LinkAdmin)
admin.site.register(BodyCache, BodyCacheAdmin)

