#include "QmlGaugeDefinition.hpp"

void QmlGaugeDefinition::colorZoneRowDeleted(int index)
{
    d_definition->colorZones.removeAt(index);
    checkForUnsavedChanges();
}

void QmlGaugeDefinition::gradRowDeleted(int index)
{
    d_definition->grads.removeAt(index);
    checkForUnsavedChanges();
}

void QmlGaugeDefinition::textGradRowDeleted(int index)
{
    d_definition->textGrads.removeAt(index);
    checkForUnsavedChanges();
}

void QmlGaugeDefinition::colorZoneRowModified(int index, const definitions::ColorZone &row)
{
    d_definition->colorZones[index] = row;
    checkForUnsavedChanges();
}

void QmlGaugeDefinition::gradRowModified(int index, const definitions::GradDef &row)
{
    d_definition->grads[index] = row;
    checkForUnsavedChanges();
}

void QmlGaugeDefinition::textGradRowModified(int index, const definitions::TextGradDef &row)
{
    d_definition->textGrads[index] = row;
    checkForUnsavedChanges();
}

void QmlGaugeDefinition::colorZoneRowAppended(const definitions::ColorZone &row)
{
    d_definition->colorZones.append(row);
    checkForUnsavedChanges();
}

void QmlGaugeDefinition::gradRowAppended(const definitions::GradDef &row)
{
    d_definition->grads.append(row);
    checkForUnsavedChanges();
}

void QmlGaugeDefinition::textGradRowAppended(const definitions::TextGradDef &row)
{
    d_definition->textGrads.append(row);
    checkForUnsavedChanges();
}

void QmlGaugeDefinition::colorZoneRowInserted(int index, const definitions::ColorZone &row)
{
    d_definition->colorZones.insert(index, row);
    checkForUnsavedChanges();
}

void QmlGaugeDefinition::gradRowInserted(int index, const definitions::GradDef &row)
{
    d_definition->grads.insert(index, row);
    checkForUnsavedChanges();
}

void QmlGaugeDefinition::textGradRowInserted(int index, const definitions::TextGradDef &row)
{
    d_definition->textGrads.insert(index, row);
    checkForUnsavedChanges();
}

void QmlGaugeDefinition::gradsGenerated(const QList<definitions::GradDef> &newData)
{
    d_definition->grads = newData;
    checkForUnsavedChanges();
}

void QmlGaugeDefinition::textGradsGenerated(const QList<definitions::TextGradDef> &newData)
{
    d_definition->textGrads = newData;
    checkForUnsavedChanges();
}