(function ($) {
  Drupal.behaviors.simplemeta = {
    attach: function (context) {
      var forms = $('#simplemeta-meta-form.simplemeta-meta-form-ajax:not(.simplemeta-processed)', context);
      forms.each(function (index) {

        var form = $(this),
            close = $('<span class="form-close"></span>').prependTo(form);
        close.text(Drupal.t('Meta'));
        form.addClass('hidden').css({left: (-form.outerWidth()) + 'px'});

        close.click(function (event) {
          var $this = $(this);
          if (form.hasClass('hidden')) {
            form.stop(true).animate({left: 0});
            $this.text(Drupal.t('Close'));
          }
          else {
            form.stop(true).animate({left: -form.outerWidth()});
            $this.text(Drupal.t('Meta'));
          }
          form.toggleClass('hidden');
        });
      });
      forms.addClass('simplemeta-processed');
    }
  };
})(jQuery);