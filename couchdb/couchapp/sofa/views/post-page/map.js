function(doc) {
  // todo make commonjs
  // !code helpers/md5.js
  
  if (doc.type == "post") {
    emit([doc._id], doc);
  } else if (doc.type == "comment") {
    if (doc.commenter && doc.commenter.email && !doc.commenter.gravatar_url) {
      doc.commenter.gravatar = hex_md5(doc.commenter.email);      
    }
    emit([doc.post_id, doc.created_at], doc);
  }
};