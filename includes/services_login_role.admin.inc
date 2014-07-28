<?php

/**
 * 设置允许登陆的角色
 */
function services_login_role_setting_form($form, &$form_state) {
	$roles = user_roles(TRUE);
	
	$form['roles'] = array(
		'#type' => 'checkboxes',
		'#title' => t('请选择允许通过services登陆的角色'),
		'#options' => $roles,
		'#default_value' => variable_get('services_login_allowed_roles', array()),
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('确认提交')
	);
	
	return $form;
}

function services_login_role_setting_form_submit($form, &$form_state) {
	form_state_values_clean($form_state);
	
	$roles = $form_state['values']['roles'];
	$roles = array_filter($roles);

	variable_set('services_login_allowed_roles', $roles);
}