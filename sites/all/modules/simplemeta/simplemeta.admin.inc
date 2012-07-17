<?php

/**
 * Simplemeta settings form
 */
//function simplemeta_settings_form($form, &$form_state) {
//  $form['simplemeta_form_enable'] = array(
//    '#type' => 'checkbox',
//    '#title' => t('Enable Add Meta Tags Form'),
//    '#description' => t('If enabled, form will appear on pages'),
//    '#default_value' => variable_get('simplemeta_form_enable', FALSE),
//    '#return_value' => TRUE,
//  );
//  return system_settings_form($form);
//}

function simplemeta_meta_list() {
  $info = simplemeta_get_info();
  $query = db_select('simplemeta', 's')
    ->extend('PagerDefault')
    ->fields('s')
    ->orderBy('s.sid', 'DESC')->limit(20);
  $result = $query->execute();
  
  $items = array();
  while ($meta = $result->fetchObject()) {
    $meta->data = unserialize($meta->data);
    $items[] = $meta;
  }
  
  return theme('simplemeta_meta_list', array('items' => $items)) . theme('pager');
}

function simplemeta_add() {
  $meta = new stdClass();
  $meta->data = array();
  $meta->language = '';
  return drupal_get_form('simplemeta_meta_form', $meta);
}

function simplemeta_meta_delete_confirm($form, &$form_state, $meta) {
  $form['sid'] = array(
    '#type' => 'value', 
    '#value' => $meta->sid,
  );

  return confirm_form($form, 
    t('Are you sure you want to delete Simplemeta %sid?', array('%sid' => $meta->sid)), 
    isset($_GET['destination']) ? $_GET['destination'] : 'admin/content/simplemeta/' . $meta->sid . '/edit', 
    t('This action cannot be undone.'), 
    t('Delete'), 
    t('Cancel')
  );
}

function simplemeta_meta_delete_confirm_submit($form, &$form_state) {
  if ($form_state['values']['confirm']) {
    simplemeta_meta_delete($form_state['values']['sid']);
    cache_clear_all('*', 'cache_simplemeta', TRUE);
  }
  $form_state['redirect'] = 'admin/content/simplemeta/list';
}

