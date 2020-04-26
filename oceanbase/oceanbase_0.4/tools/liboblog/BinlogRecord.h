/**
 * Copyright (c) 2012 Taobao.com
 * All rights reserved.
 *
 * �ļ����ƣ�BinlogRecord.h
 * ժҪ��ͨ��Binlog���������ļ�¼��Ϣ����
 * ���ߣ�Benkong <benkong@taobao.com>
 *       Jierui.lj <jierui.lj@taobao.com>
 * ���ڣ�2012.3.13
 *       2012.8.9 ͳһ���������ʽ���ֶκ�BinlogRecord, Binlog�Ĺ���
 *       2013.5.22 beknong ȥ���������������ݿ�ĸ�ʽ������
 */
#ifndef _BINLOG_RECORD_H_
#define _BINLOG_RECORD_H_

#include "ob_define.h"
#include "BR.h"

namespace oceanbase
{
namespace liboblog
{

struct BRInfo;

class BinlogRecord : public IBinlogRecord
{
public:
    /**
     * ����һ����¼
     * @param timestamp  ʱ���
     * @param tbleMeta   ��Ӧ���������Ϣ
     */
    BinlogRecord(time_t timestamp, ITableMeta *tblMeta);

    /**
     * ����һ��ֻ����¼
     * @param ptr   ������
     * @param size  ptr��ռ�ֽ���
     */
	BinlogRecord(const void *ptr, size_t size);
	BinlogRecord(bool creating=true);

    virtual ~BinlogRecord();

	/**
	 * ����ֻ����¼
     * @param ptr   ������
     * @param size  ptr��ռ�ֽ���
	 * @return 0:�ɹ���<0: ʧ��
	 */
	int parse(const void *ptr, size_t size);

	/**
	 * �Ƿ�����ɹ�
	 * @return true/false
	 */
	bool parsedOK();

	/**
	 * ֻ��������ʵ����Ч���ֽ�����parse()��ʱ������size�ȱ���Ч���ݳ�
	 * @return �ֽ���
	 */
	size_t getRealSize();

    /**
     * ����һ������ǰ��column��ֵ
     * @parm colName   column����
     * @parm val       column�ľ�ֵ
     * @return 0: �ɹ�; <0: ʧ��
     */
    int putOld(std::string *val);

    /**
     * ����һ�����º��column��ֵ
     * @parm colName   column����
     * @parm val       column����ֵ
     * @return 0: �ɹ�; <0: ʧ��
     */
    int putNew(std::string *val);

    /**
     * ��ȡ����ǰcolumn��ֵ��ӳ���
     * @return column name => column value
     */
    const std::vector<std::string *>& oldCols();
	IStrArray* parsedOldCols() const;

    /**
     * ��ȡ���º�column��ֵ��ӳ���
     * @return column name => column value
     */
    const std::vector<std::string *>& newCols();
	IStrArray* parsedNewCols() const;

    IStrArray* parsedColNames() const;

    const uint8_t *parsedColTypes() const;

    void setInstance(const char *instance);
    const char* instance() const;

	void setDbname(const char *dbname);
	const char *dbname() const;

    void setTbname(const char *tbname);
    const char* tbname() const;

    void setPKValue(const char *pkValue);
	const char* pkValue() const;

    bool conflicts(const IBinlogRecord *);
    bool conflicts(const BinlogRecord *);

    /**
     * ���л�Ϊ�ַ���
     * @return ��NULL: �ɹ�; NULL: ʧ��
     */
    std::string* toParsedString();
	const std::string* toString();

	void clear();
    void clearNew();
    void clearOld();

    bool isAnyChanged() const;
    bool isTxnEnded() const;

    int recordType();
    int setRecordType(int aType);

	const char* recordEncoding();

    void setTimestamp(time_t timestamp);
    time_t getTimestamp();

	void setCheckpoint(unsigned file, unsigned offset);
    const char* getCheckpoint();
    unsigned getCheckpoint1();
    unsigned getCheckpoint2();
    unsigned getFileNameOffset();
    unsigned getFileOffset();

	void setLastInLogevent(bool b);
	bool lastInLogevent();

    void setId(uint64_t id);
    uint64_t id();

	void setTableMeta(ITableMeta *tblMeta);
    ITableMeta* getTableMeta();

    int getSrcType() const;

	long* getTimemark(size_t& length) {/*TODO*/ UNUSED(length); return NULL;};

	void addTimemark(long time) {/*TODO*/ UNUSED(time);};

private:
	BRInfo *m_br;
    std::string m_buf;
};

}
}

#endif

