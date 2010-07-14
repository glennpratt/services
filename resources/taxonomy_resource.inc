<?php
// $Id: taxonomy_service.inc,v 1.1.2.6.2.1 2009/12/05 01:42:39 heyrocker Exp $
/**
 * @file
 *  Link general taxonomy functionalities to services module.
 */

function _taxonomy_resource_definition() {
  if (!module_exists('taxonomy')) {
    return array();
  }

  return array(
    'taxonomy_term' => array(
      'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/taxonomy_resource'),
      'retrieve' => array(
        'callback' => '_taxonomy_term_resource_retrieve',
        'args' => array(
          array(
            'name' => 'tid',
            'optional' => FALSE,
            'source' => array('path' => 0),
            'type' => 'int',
            'description' => 'The tid of the taxonomy term to get',
          ),
        ),
        'access callback' => '_taxonomy_resource_access',
        'access arguments' => array('view'),
        'access arguments append' => TRUE,
      ),
      'create' => array(
        'callback' => '_taxonomy_term_resource_create',
        'args' => array(
          array(
            'name' => 'term',
            'optional' => FALSE,
            'source' => 'data',
            'description' => 'The taxonomy term object to create',
            'type' => 'struct',
          ),
        ),
        'access callback' => '_taxonomy_resource_access',
        'access arguments' => array('create'),
        'access arguments append' => TRUE,
      ),
      'update' => array(
        'callback' => '_taxonomy_term_resource_update',
        'args' => array(
          array(
            'name' => 'term',
            'optional' => FALSE,
            'source' => 'data',
            'description' => 'The taxonomy term data to update',
            'type' => 'struct',
          ),
        ),
        'access callback' => '_taxonomy_resource_access',
        'access arguments' => array('update'),
        'access arguments append' => TRUE,
      ),
      'delete' => array(
        'callback' => '_taxonomy_term_resource_delete',
        'args' => array(
          array(
            'name' => 'tid',
            'optional' => FALSE,
            'source' => array('path' => 0),
          ),
        ),
        'access callback' => '_taxonomy_resource_access',
        'access arguments' => array('delete'),
        'access arguments append' => TRUE,
      ),
      'index' => array(
        'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/taxonomy_resource'),
        'callback' => '_taxonomy_term_resource_index',
        'args' => array(
          array(
            'name' => 'page',
            'optional' => TRUE,
            'type' => 'int',
            'description' => 'The zero-based index of the page to get, defaults to 0.',
            'default value' => 0,
            'source' => array('param' => 'page'),
          ),
          array(
            'name' => 'fields',
            'optional' => TRUE,
            'type' => 'string',
            'description' => 'The fields to get.',
            'default value' => '',
            'source' => array('param' => 'fields'),
          ),
          array(
            'name' => 'parameters',
            'optional' => TRUE,
            'type' => 'struct',
            'description' => 'Parameters',
            'default value' => NULL,
            'source' => 'param',
          ),
        ),
        'access arguments' => array('access user profiles'),
        'access arguments append' => FALSE,
      ),
      // TODO: term specific actions need to be implemented (see: taxonomy_service_get_tree / taxonomy_service_select_nodes)
    ),
    'taxonomy_vocabulary' => array(
      'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/taxonomy_resource'),
      'retrieve' => array(
        'callback' => '_taxonomy_vocabulary_resource_retrieve',
        'args' => array(
          array(
            'name' => 'vid',
            'optional' => FALSE,
            'source' => array('path' => 0),
            'type' => 'int',
            'description' => 'The vid of the taxonomy vocabulary to get',
          ),
        ),
        'access callback' => '_taxonomy_resource_access',
        'access arguments' => array('view'),
        'access arguments append' => TRUE,
      ),
      'create' => array(
        'callback' => '_taxonomy_vocabulary_resource_create',
        'args' => array(
          array(
            'name' => 'vocabulary',
            'optional' => FALSE,
            'source' => 'data',
            'description' => 'The taxonomy vocabulary object to create',
            'type' => 'struct',
          ),
        ),
        'access callback' => '_taxonomy_resource_access',
        'access arguments' => array('create'),
        'access arguments append' => TRUE,
      ),
      'update' => array(
        'callback' => '_taxonomy_vocabulary_resource_update',
        'args' => array(
          array(
            'name' => 'vocabulary',
            'optional' => FALSE,
            'source' => 'data',
            'description' => 'The taxonomy vocabulary data to update',
            'type' => 'struct',
          ),
        ),
        'access callback' => '_taxonomy_resource_access',
        'access arguments' => array('update'),
        'access arguments append' => TRUE,
      ),
      'delete' => array(
        'callback' => '_taxonomy_vocabulary_resource_delete',
        'args' => array(
          array(
            'name' => 'vid',
            'optional' => FALSE,
            'source' => array('path' => 0),
          ),
        ),
        'access callback' => '_taxonomy_resource_access',
        'access arguments' => array('delete'),
        'access arguments append' => TRUE,
      ),
      'index' => array(
        'file' => array('type' => 'inc', 'module' => 'services', 'name' => 'resources/taxonomy_resource'),
        'callback' => '_taxonomy_vocabulary_resource_index',
        'args' => array(
          array(
            'name' => 'page',
            'optional' => TRUE,
            'type' => 'int',
            'description' => 'The zero-based index of the page to get, defaults to 0.',
            'default value' => 0,
            'source' => array('param' => 'page'),
          ),
          array(
            'name' => 'fields',
            'optional' => TRUE,
            'type' => 'string',
            'description' => 'The fields to get.',
            'default value' => '',
            'source' => array('param' => 'fields'),
          ),
          array(
            'name' => 'parameters',
            'optional' => TRUE,
            'type' => 'struct',
            'description' => 'Parameters',
            'default value' => NULL,
            'source' => 'param',
          ),
        ),
        'access arguments' => array('access user profiles'),
        'access arguments append' => FALSE,
      ),
    ),
  );
}

/**
 * Services interface to _taxonomy_term_resource_retrieve().
 *
 * @see
 *
 */
function _taxonomy_term_resource_retrieve($tid = NULL){
  return taxonomy_get_term($tid);
}

/**
 * Services interface to _taxonomy_term_resource_create().
 *
 * @see
 *
 */
function _taxonomy_term_resource_create($term=NULL){
  if (!is_array($term)) {
    $term = (array) $term;
  }
  return taxonomy_save_term($term);
}

/**
 * Services interface to _taxonomy_term_resource_update().
 *
 * @see
 *
 */
function _taxonomy_term_resource_update($term=NULL){
  return _taxonomy_term_resource_create($term);
}

/**
 * Services interface to _taxonomy_term_resource_delete().
 *
 * @see
 *
 */
function _taxonomy_term_resource_delete($tid=NULL){
  return taxonomy_del_term($tid);
}


/**
 * Services interface to _taxonomy_vocabulary_resource_retrieve().
 *
 * @see
 *
 */
function _taxonomy_vocabulary_resource_retrieve($vid=NULL){
  return taxonomy_vocabulary_load($vid);
}

/**
 * Services interface to _taxonomy_vocabulary_resource_create().
 *
 * @see
 *
 */
function _taxonomy_vocabulary_resource_create($vocabulary){
  if (!is_array($vocabulary)) {
    $vocabulary = (array) $vocabulary;
  }
  return taxonomy_save_vocabulary($vocabulary);
}

/**
 * Services interface to _taxonomy_vocabulary_resource_update().
 *
 * @see
 *
 */
function _taxonomy_vocabulary_resource_update($vocabulary){
  return _taxonomy_vocabulary_resource_create($vocabulary);
}

/**
 * Services interface to _taxonomy_vocabulary_resource_delete().
 *
 * @see
 *
 */
function _taxonomy_vocabulary_resource_delete($vid=NULL){
  return taxonomy_del_vocabulary($vid);
}



/**
 * Services interface to taxonomy_get_tree().
 *
 * @see
 *   taxonomy_get_tree()
 */
function taxonomy_service_get_tree($vid, $parent = 0, $max_depth = NULL) {
  return taxonomy_get_tree($vid, $parent, -1, $max_depth);
}

/**
 * Services interface to taxonomy_select_nodes().
 *
 * Note that where taxonomy_select_nodes() returns the results
 * of a db_query(), this function returns an array of node objects.
 *
 * @see
 *   taxonomy_select_nodes().
 * @return 
 *   An array of node objects.
 */
function taxonomy_service_select_nodes($tids = array(), $fields = array(), $operator = 'or', $depth = 0, $pager = TRUE, $order = 'n.sticky DESC, n.created DESC') {
  $result = taxonomy_select_nodes($tids, $operator, $depth, $pager, $order);
  while ($node = db_fetch_object($result)) {
    $nodes[] = services_node_load(node_load($node->nid), $fields);
  }

  return $nodes;
}

function _taxonomy_vocabulary_resource_index($page = 0, $fields = array(), $parameters = array()) {
  $params = array();
  $table = 'vocabulary';
  $table_id = 'vid';
  $schema = drupal_get_schema($table);

  $parameters = (array)$parameters;

  $verified_fields = array();
  foreach($fields as $field) {
    if (in_array($field, array_keys($schema['fields']))) {
      $verified_fields[] = $field;
    }
  }
  $fieldset = (!empty($verified_fields)?implode(', ', $verified_fields):'*');

  // Only allow fields that actually exist.
  foreach($parameters as $key => $param) {
    if (in_array($key, array_keys($schema['fields']))) {
      $where[] = $key . " = " . db_type_placeholder($schema['fields'][$key]['type']);
      $params[] = $param;
    }
  }
  $sql = "SELECT $fieldset FROM {$table}" . ((!empty($where))?' WHERE ' . implode(' AND ', $where):'');

  $res = db_query_range($sql, $params, $page * 20, 20);

  $rows = array();
  while ($row = db_fetch_object($res)) {
    $rows[$row->{$table_id}] = $row;
  }
  return $rows;
}

function _taxonomy_term_resource_index($page = 0, $fields = array(), $parameters = array()) {
  $params = array();
  $table = 'term_data';
  $table_id = 'tid';
  $schema = drupal_get_schema($table);

  $parameters = (array)$parameters;

  $verified_fields = array();
  foreach($fields as $field) {
    if (in_array($field, array_keys($schema['fields']))) {
      $verified_fields[] = $field;
    }
  }
  $fieldset = (!empty($verified_fields)?implode(', ', $verified_fields):'*');

  // Only allow fields that actually exist.
  foreach($parameters as $key => $param) {
    if (in_array($key, array_keys($schema['fields']))) {
      $where[] = $key . " = " . db_type_placeholder($schema['fields'][$key]['type']);
      $params[] = $param;
    }
  }
  $sql = "SELECT $fieldset FROM {$table}" . ((!empty($where))?' WHERE ' . implode(' AND ', $where):'');

  $res = db_query_range($sql, $params, $page * 20, 20);

  $rows = array();
  while ($row = db_fetch_object($res)) {
    $rows[$row->{$table_id}] = $row;
  }
  return $rows;
}