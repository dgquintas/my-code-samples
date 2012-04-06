from miweb.blog.models import Entry, Comment
from django.contrib import admin

class EntryAdmin(admin.ModelAdmin):
  prepopulated_fields = {"slug": ("title",) }

class CommentAdmin(admin.ModelAdmin):
  pass


admin.site.register(Entry, EntryAdmin)
admin.site.register(Comment, CommentAdmin)

