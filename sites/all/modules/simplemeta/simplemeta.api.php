<?php

function hook_simplemeta_info() {
  $info = array();
  $info['description'] = array(
    // required
    'title' => t('Description'),
    // required
    'form' => 'simplemeta_form_description',
    'validate' => NULL,
    'submit' => NULL,
    // required
    'theme' => 'simplemeta_meta_description',
  );
  return $info;
}

/**
 * @param object $meta meta object operation is performed on
 * @param string $op performed operation: insert, update or delete
 */

function hook_simplemeta($meta, $op) {
  
}
