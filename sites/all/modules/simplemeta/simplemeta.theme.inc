<?php

/**
 * @file theming
 */

function theme_simplemeta_meta_list($vars) {
  $items = $vars['items'];
  $header = array(t('Path'), t('Alias'), t('Action'));
  $rows = array();
  foreach ($items as $meta) {
    // @todo think about how to determine that path is pattern, like node/%/edit
    $pattern = (strpos($meta->path, '%') !== FALSE);
    $alias = drupal_get_path_alias($meta->path);
    $rows[] = array(
      (!$pattern) ? l($meta->path, $meta->path) : check_plain($meta->path),
      ((!$pattern) && ($alias != $meta->path)) ? l($alias, $meta->path) : '-',
      l(t('Edit'), 'admin/content/simplemeta/' . $meta->sid . '/edit') . ' | ' . l(t('Delete'), 'admin/content/simplemeta/' . $meta->sid . '/delete'),
    );
  }
  if (empty($rows)) {
    $rows[] = array(array('data' => t('There is no saved meta data'), 'colspan' => 3));
  }
  return theme('table', array('header' => $header, 'rows' => $rows));
}

function theme_simplemeta_meta_title($vars) {
  $meta = $vars['meta'];
  return '';
}

function theme_simplemeta_meta_description($vars) {
  $meta = $vars['meta'];
   if (!empty($meta->data['description'])) {
     // @todo think about
     return '<meta name="description" content="' . trim(strip_tags(decode_entities($meta->data['description']))) . '" />';
   }
   return '';
}

function theme_simplemeta_meta_keywords($vars) {
  $meta = $vars['meta'];
  if (!empty($meta->data['keywords'])) {
    // @todo think about
    return '<meta name="keywords" content="' . trim(strip_tags(decode_entities($meta->data['keywords']))) . '" />';
  }
  return '';
}
